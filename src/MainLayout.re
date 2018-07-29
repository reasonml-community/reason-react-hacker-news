open Utils;

requireCSS("src/MainLayout.css");

let component = ReasonReact.statelessComponent("MainLayout");

type contentType;

let make = children => {
  ...component,
  render: _self =>
    <div className="MainLayout">
      <div className="MainLayout_Header">
        <h1> (ReasonReact.string("Reason React Hacker News")) </h1>
        <div className="MainLayout_Header_Menu">
          <Link href="/"> (ReasonReact.string("Home")) </Link>
          <a
            href="https://github.com/reasonml-community/reason-react-hacker-news"
            target="_blank">
            (ReasonReact.string("About"))
          </a>
        </div>
      </div>
      <div className="MainLayout_Content"> children[0] </div>
    </div>,
};
