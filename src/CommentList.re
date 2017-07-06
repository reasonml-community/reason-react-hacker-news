open Utils;

requireCSS "src/CommentList.css";

type state = {collapsed_comments: JSSet.set int};
let name = "CommentList";
let component = ReasonReact.statefulComponent name;

let make story::(story: StoryData.story_with_comments) _children => {
  let toggleComment collapsed (idMaybe: option string) =>
    switch idMaybe {
    | Some idString =>
      let id = int_of_string idString;
      if (JSSet.has collapsed id) {
        JSSet.remove collapsed id
      } else {
        JSSet.add collapsed id
      }
    | None => collapsed
    };
  let getCommentIdFromEvent (event: ReactEventRe.Mouse.t) =>
    getAttribute (ReactDOMRe.domElementToObj (ReactEventRe.Mouse.currentTarget event)) "name";
  let handleToggle event {ReasonReact.state} =>
    ReasonReact.Update {
      collapsed_comments: toggleComment state.collapsed_comments (getCommentIdFromEvent event)
    };
  let renderCommentText (textMaybe: option string) =>
    switch textMaybe {
    | Some text => <div dangerouslySetInnerHTML=(dangerousHtml text) />
    | None => textEl "missing comment"
    };
  let rec renderCommentKids self (comment: StoryData.comment_present) =>
    renderCommentList self comment.kids
  and renderComment self (id: int) => {
    let {ReasonReact.state} = self;
    let commentMaybe = JSMap.get story.comments id;
    let commentContent =
      switch commentMaybe {
      | Some commentPresentOrDeleted =>
        switch commentPresentOrDeleted {
        | StoryData.CommentPresent comment =>
          let openComment = not (JSSet.has state.collapsed_comments comment.id);
          let commentBody =
            if openComment {
              <div className="CommentList_commentBody">
                (renderCommentText comment.text)
                (renderCommentKids self comment)
              </div>
            } else {
              <noscript />
            };
          <div className="CommentList_comment">
            <div
              className="CommentList_disclosureRow CommentList_inline"
              name=(string_of_int comment.id)
              onClick=(self.update handleToggle)>
              <img
                alt=(openComment ? "hide" : "show")
                src=(
                  openComment ?
                    requireAssetURI "src/disclosure90.png" : requireAssetURI "src/disclosure.png"
                )
                className="CommentList_disclosure CommentList_muted"
              />
              <span className="CommentList_muted">
                (textEl (" " ^ fromNow comment.time ^ " by " ^ comment.by))
              </span>
            </div>
            commentBody
          </div>
        | StoryData.CommentDeleted _ => <div> (textEl "[deleted]") </div>
        }
      | None => raise Exit
      };
    <div key=(string_of_int id)> commentContent </div>
  }
  and renderCommentList self (commentIds: option (array int)) =>
    switch commentIds {
    | Some ids =>
      let commentList = Array.map (fun id => renderComment self id) ids;
      <div> (ReasonReact.arrayToElement commentList) </div>
    | None => <div />
    };

  {
    ...component,
    initialState: fun () => {collapsed_comments: JSSet.create ([||]: array int)},
    render: fun self => {
      renderCommentList self story.kids
    },
  };
};
