open Utils;
let styles = requireCSSModule("src/Pagination.module.css");

let component = ReasonReact.statelessComponent("Pagination");
let make = (~storyType, ~page, ~maxPages, _children) => {
  let prev = page - 1;
  let next = page + 1;
  {
    ...component,
    render: _self =>
      <p className={className(styles, "pagination")}>
        <Link href={j|/$storyType/$prev|j} className={
          classNameFilter(styles, [|("navigate", true), ("disabled", page <= 1)|])
        }>
          {textEl("< prev")}
        </Link>
        <span className={className(styles, "pages")}>
          {textEl({j|$page/$maxPages|j})}
        </span>
        <Link href={j|/$storyType/$next|j} className={
          classNameFilter(styles, [|("navigate", true), ("disabled", page >= maxPages)|])
        }>
          {textEl("next >")}
        </Link>
      </p>
    }
  }
