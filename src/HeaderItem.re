open Utils;
let styles = requireCSSModule("src/Header.module.css");
let cn = (name) => className(styles, name);

let component = ReasonReact.statelessComponent("NavItem");
let make = (~href, ~text, ~url, ~active, _children) => {
  {
    ...component,
    render: (self) =>
    <li className={cn("item")}>
      <Link href={href} className={classNameFilter(styles, [|("link", true), ("active", active)|])}>
        {textEl(text)}
      </Link>
    </li>
    }
  }
